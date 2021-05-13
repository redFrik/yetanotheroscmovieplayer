//note: if you have both python3 and python installed use pip3 and python3 below

//first cd to this directory and
pip install python-osc

//if you’re on raspbian you might need to install pyosc like this:
git clone https://github.com/ptone/pyosc.git --depth 1
cd pyosc
sudo ./setup.py install
cd ..

//then start the yetanotheroscmovieplayer application
//here we assume the app is running locally (127.0.0.1)


//quick tests (from the terminal - assumes the app is running on 127.0.0.1)
python startmovie.py
python stop.py



//interactive examples (start by typing ’python’ in terminal)
from pythonosc import udp_client
app= udp_client.SimpleUDPClient('127.0.0.1', 61000)

app.send_message('/start', ['kjhkjh.png', 10]) #fade in a still image

app.send_message('/stop', 10)

app.send_message('/start', ['yetanotherdemo.mov', 100, 1]) #loop off (0= no loop, 1= normal loop, 2= palindrome)

app.send_message('/info', []) #toggle info (also key 'i')

app.send_message('/fps', 15) #set framerate

app.send_message('/speed', 0.5) #set playback rate

app.send_message('/mode', 0) #fill screen (ignore original aspect ratio)
app.send_message('/mode', 1) #no scaling (original dimensions)
app.send_message('/mode', 2) #scale to fit width (crop height)
app.send_message('/mode', 3) #scale to fit height (crop width)

app.send_message('/exit', [])
