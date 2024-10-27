import random

alphabet = "abcdefghijklmnopqrstuvwxyz0123456789"

def generate_random_string(length):
    a = [random.choice(alphabet) for i in range(length)]
    return ''.join(map(str,a))

def caesar_cipher_encode(s):
    a = [alphabet[alphabet.index(i) - 3] for i in s]
    return ''.join(map(str,a))

def caesar_cipher_decode(s):
    a = [alphabet[alphabet.index(i) + 3] if alphabet.index(i) + 3 < len(alphabet) else (alphabet.index(i) + 3) % len(alphabet) for i in s]
    return ''.join(map(str,a))
