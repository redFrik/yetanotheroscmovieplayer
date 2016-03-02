from OSC import OSCClient, OSCMessage

app= OSCClient()
app.connect(('127.0.0.1', 61000)) #send address
msg= OSCMessage('/start')
msg.append(['yetanotherdemo.mov', 200, 1])  #loop on (0= no loop, 1= normal loop, 2= palindrome)
app.send(msg)  #fade in over 200 frames
app.close()
