import os, random
import util

directory_name = "project_1/final_files/"

os.mkdir(directory_name + "files/")

message_file_num = random.randint(0, 24)

with open(directory_name + "message.txt", 'r') as f:
    message = f.read()

for i in range(100):
    if i == message_file_num:
        with open(directory_name + "files/" + util.caesar_cipher_encode(message), "w") as current_file:
            current_file.write(util.caesar_cipher_encode('k43s3rm0r3l1k31337sp34k'))
    else:
        with open(directory_name + "files/" + util.generate_random_string(20), "w") as current_file:
            current_file.write(util.caesar_cipher_encode(util.generate_random_string(23)))


