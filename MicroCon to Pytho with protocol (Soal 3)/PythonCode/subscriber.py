import paho.mqtt.client as mqtt
import time

mqtt_broker = "free.mqtt.iyoti.id"
port = 1883
topic_sub = 'robotikid/pub'
topic_pub = 'robotikid/sub'
time_interval = 1

#callback jika sukses terhubung
def on_connect(client, userdata, flags, rc):
    print('Connected with result code '+str(rc))
    client.subscribe(topic_sub)

# callback menerima pesan
def on_message(client, userdata, msg):
    print("Terima Dari: {}, Nilai: {}".format(msg.topic, msg.payload))

client = mqtt.Client()

# setting fungsi callback
client.on_connect = on_connect
client.on_message = on_message

# menghubungkan
client.connect(mqtt_broker, port)

# Publish a message
client.publish(topic_pub, payload='Mulai Dari Laptop')
client.loop_forever()