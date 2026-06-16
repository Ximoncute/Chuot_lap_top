from flask import Flask, request
import pyautogui
import threading
import time

app = Flask(__name__)

dx = 0
dy = 0

@app.route('/click')
def click():
    pyautogui.click()
    return "OK"

@app.route('/move')
def move():
    global dx, dy
    dx = int(request.args.get('dx'))
    dy = int(request.args.get('dy'))
    return "OK"

def mouse_task():
    global dx, dy

    while True:
        if dx != 0 or dy != 0:
            pyautogui.moveRel(dx, dy)
        time.sleep(0.01)

threading.Thread(target=mouse_task, daemon=True).start()

app.run(host='0.0.0.0', port=5000)