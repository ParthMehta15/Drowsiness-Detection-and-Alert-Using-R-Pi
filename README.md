# Drowsiness-Detection-and-Alert-Using-R-Pi

The system is used to detect if the the driver is drowsy and if yes, ring the buzzer, and send alert to predefined contacts along with GPS coordinates also reduce speed also start parking lights.
The system can greatly reduce road accidnets.


Also download: [shape_predictor_68_face_landmarks.dat](https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2)


Upload FINAL_arduino.io file on Arduino and drowsiness_detection_Rpie.py on Raspberry Pie and connect the wires as shown in figure.

Run python file as: python pi_detect_drowsiness.py --cascade haarcascade_frontalface_default.xml --shape-predictor shape_predictor_68_face_landmarks.dat
