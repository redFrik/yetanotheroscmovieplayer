from pythonosc import udp_client

app= udp_client.SimpleUDPClient('127.0.0.1', 61000) #send address
app.send_message('/start', ['yetanotherdemo.mov', 200, 1]) #fade in over 200 frames, loop on (0= no loop, 1= normal loop, 2= palindrome)
