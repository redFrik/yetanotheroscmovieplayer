from OSC import OSCClient, OSCMessage

app= OSCClient()
app.connect(('127.0.0.1', 61000)) #send address
msg= OSCMessage('/stop')
msg.append(100)
app.send(msg)  #fade out over 100 frames
app.close()
