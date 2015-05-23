import time
import serial
from twython import TwythonStreamer

# Search terms
TERMS = '#gay'

# Twitter application authentication
APP_KEY = '2pbY32s3nZzckqvMAbK8I0LKi'
APP_SECRET = 'aEpdBUxHl0G0DAepipi6ZXThWt9VCaYQ2Gf8FGQNFA22BqGrKJ'
OAUTH_TOKEN = '52750250-9JdCf6J6WXnCiL5fzwwGrHqHq0gw3YD07ZFKqyn3w'
OAUTH_TOKEN_SECRET = 'xo724qyBBALSNFza1irz1eNjx0w1XI1I3OZDMNRDjqh0w'

serial = serial.Serial('/dev/ttyACM1', 19200)

## check serial port
def checkokay():
  ser.flushInput()
  time.sleep(3)
  line=ser.readline()
  time.sleep(3)

  if line == ' ':
    line=ser.readline()
  print 'here'

## Welcome message
print 'Welcome To GayBox !'

# Setup callbacks from Twython Streamer
class BlinkyStreamer(TwythonStreamer):
        def on_success(self, data):
                if 'text' in data:
                        print data['text'].encode('utf-8')
                        print
                        serial.write('1')

# Create streamer
try:
        stream = BlinkyStreamer(APP_KEY, APP_SECRET, OAUTH_TOKEN, OAUTH_TOKEN_SECRET)
        stream.statuses.filter(track=TERMS)
except KeyboardInterrupt:
        print "KeyboardInterrupt"