//first cd to this directory and
pip install pyosc

//if you’re on raspbian jessie you might need to install pyosc like this:
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
from OSC import OSCClient, OSCMessage
app= OSCClient()
app.connect(('127.0.0.1', 61000))

msg= OSCMessage('/start')
msg.append(['kjhkjh.png', 10])
app.send(msg)  #fade in a still image

msg= OSCMessage('/stop')
msg.append(10)
app.send(msg)

msg= OSCMessage('/start')
msg.append(['yetanotherdemo.mov', 100, 0])
app.send(msg)  #loop off (0= no loop, 1= normal loop, 2= palindrome)

msg= OSCMessage('/info')
app.send(msg)  #toggle info (also key 'i')

msg= OSCMessage('/fps')
msg.append(15)
app.send(msg)  #set framerate

msg= OSCMessage('/speed')
msg.append(0.5)
app.send(msg)  #set playback rate

msg= OSCMessage('/mode')
msg.insert(0, 0)
app.send(msg)  #fill screen (ignore original aspect ratio)
msg.insert(0, 1)
app.send(msg)  #no scaling (original dimensions)
msg.insert(0, 2)
app.send(msg)  #scale to fit width (crop height)
msg.insert(0, 3)
app.send(msg)  #scale to fit height (crop width)

app.close()
