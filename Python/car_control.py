import cv2
import mediapipe as mp
import socket

# ---------------- UDP ----------------
ESP32_IP = "192.168.4.1"
PORT = 4210
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# ---------------- MEDIAPIPE ----------------
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    max_num_hands=1,
    min_detection_confidence=0.85,
    min_tracking_confidence=0.85
)
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

# ---------------- GESTURE HELPERS ----------------
def finger_up(lm, tip, pip):
    return lm[tip].y < lm[pip].y

def get_gesture(lm):
    index  = finger_up(lm, 8, 6)
    middle = finger_up(lm, 12, 10)
    ring   = finger_up(lm, 16, 14)
    pinky  = finger_up(lm, 20, 18)

    if index and middle and ring and pinky:
        return "F"  # Forward

    if not index and not middle and not ring and not pinky:
        return "B"  # Backward

    if index and middle and not ring and not pinky:
        return "L"  # Left

    if index and middle and ring and not pinky:
        return "R"  # Right

    if index and pinky and not middle and not ring:
        return "s"  # Servo sweep

    return "S"      # Stop


# ---------------- MAIN LOOP ----------------
last_cmd = ""

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = hands.process(rgb)

    cmd = "S"

    if result.multi_hand_landmarks:
        for hand in result.multi_hand_landmarks:
            lm = hand.landmark
            cmd = get_gesture(lm)
            mp_draw.draw_landmarks(frame, hand, mp_hands.HAND_CONNECTIONS)

    # Send ONLY if changed
    if cmd != last_cmd:
        sock.sendto(cmd.encode(), (ESP32_IP, PORT))
        print("Sent:", cmd)
        last_cmd = cmd

    cv2.putText(
        frame,
        f"CMD: {cmd}",
        (20, 50),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        (0, 255, 0),
        2
    )

    cv2.imshow("Gesture Control", frame)

    if cv2.waitKey(30) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
