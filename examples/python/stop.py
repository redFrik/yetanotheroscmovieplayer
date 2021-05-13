from pythonosc import udp_client

app= udp_client.SimpleUDPClient('127.0.0.1', 61000) #send address
app.send_message('/stop', 100) #fade out over 100 frames
