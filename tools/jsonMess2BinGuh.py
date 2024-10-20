# This is a tool for converthing aseprite .json files to a more optimised and smaller format for Elysian Enclave's animation system.
# Made By ItsDuska guuuh. Don't know why I even wrote this.


import json
import ctypes
from pathlib import Path

class HeaderBlock(ctypes.Structure):
    _fields_ = [("m_animationType", ctypes.c_uint16),
                ("m_size", ctypes.c_uint16)]

class FrameData(ctypes.Structure):
    _fields_ = [("m_x", ctypes.c_uint16),
                ("m_y", ctypes.c_uint16)]

class AnimationRawDataHeader(ctypes.Structure):
    _fields_ = [("m_width", ctypes.c_uint16),
                ("m_height", ctypes.c_uint16),
                ("m_duration", ctypes.c_uint16),
                ("m_amount", ctypes.c_uint16)]

input_file = str(input("Give .json filepath to turn in to bin spritesheet format:\n"))

guh_file = Path(input_file)

output_file = guh_file.with_suffix('.bin')

animationAmount = []
header_list = []

with open(input_file, 'r') as guh:
    data = json.load(guh)

  
    frame_width = data['frames'][0]['sourceSize']['w']
    frame_height = data['frames'][0]['sourceSize']['h']
    delay = data['frames'][0]['duration']

    prev_filename = data['frames'][0]['filename']
    currentSize = 0
    animationType = 0

    for frame_data in data['frames']:
        filename = frame_data['filename']

        if prev_filename != filename:
            header_list.append(HeaderBlock(m_animationType=animationType, m_size=currentSize))
            animationAmount.append(currentSize)

            animationType += 1
            currentSize = 0
            prev_filename = filename

        currentSize += 1


    header_list.append(HeaderBlock(m_animationType=animationType, m_size=currentSize))
    animationAmount.append(currentSize)

    header_array = HeaderBlock * len(header_list)
    header_array_instance = header_array(*header_list)

    current_index = 0

    
    animationRawDataHeader = AnimationRawDataHeader(m_width=frame_width, m_height=frame_height, m_duration=delay, m_amount=len(animationAmount))

    #for field in animationRawDataHeader._fields_:
       # print(field[0], getattr(animationRawDataHeader, field[0]))

    #for header in header_array_instance:
        #for field_name, _ in header._fields_:
            #print(f"{field_name}: {getattr(header, field_name)}")

    with open(output_file, "wb") as f:
        f.write(animationRawDataHeader)
        f.write(header_array_instance)

        for number in animationAmount:
            end_index = current_index + number

            frameData_array = (FrameData * number)()

            for index, frame_data in enumerate(data['frames'][current_index:end_index]):
                x = frame_data['frame']['x']
                y = frame_data['frame']['y']
                frameData_array[index] = FrameData(m_x=x, m_y=y)

            # for header in frameData_array:
                #for field_name, _ in header._fields_:
                    #print(f"{field_name}: {getattr(header, field_name)}")

            f.write(frameData_array)

            current_index = end_index

print(f"Tiedosto '{output_file}' on luotu onnistuneesti.")