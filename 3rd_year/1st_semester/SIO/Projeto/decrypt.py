import os
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.serialization import load_pem_public_key,load_pem_private_key
import sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding

with open("server_private.pem","rb") as ficheiro:
        server_private_key = ficheiro.read()

server_private_key = load_pem_private_key(server_private_key,password=None)

with open("public.pem","rb") as ficheiro:
        client_public_key = ficheiro.read()

client_public_key = load_pem_public_key(client_public_key)

shared_key = server_private_key.exchange(ec.ECDH(), client_public_key)

derived_key = HKDF(algorithm=hashes.SHA256(),length=32,salt=None,info=b'handshake data',).derive(shared_key)

with open("encrypted.txt","rb") as file:
        ciphered_text = file.read()

cipher = Cipher(algorithms.AES(derived_key), modes.CBC(b"1234567891011121"))
decryptor = cipher.decryptor()
ciphered_text = decryptor.update(ciphered_text) + decryptor.finalize() #returns padded data

unpadder = padding.PKCS7(128).unpadder()
data = unpadder.update(ciphered_text)
data += unpadder.finalize()

with open("decrypted.txt","wb") as file:
        file.write(ciphered_text)