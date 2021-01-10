import numpy as np
import json
from matplotlib import pyplot as plt
from matplotlib import animation

fig = plt.figure()
fps = 20

filename = 'file5_1160_786.json'

with open(filename, 'rb') as file_input:
    image_data = json.load(file_input)
    width, height = image_data['width'], image_data['height']

    def animate(num):
        frame = image_data['data'][num]
        buffer = [frame[i:i+width] for i in range(len(frame) // height)]
        image = plt.imshow(buffer)
        return [image]

    anim = animation.FuncAnimation(fig, animate,
                               frames=image_data['frames'], interval=fps, blit=True)
    videoname = filename.split('.')[0] + '.gif'
    anim.save(videoname, fps=fps)
    plt.show()