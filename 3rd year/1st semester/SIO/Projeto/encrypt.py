import os
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.serialization import load_pem_public_key,load_pem_private_key
import sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.primitives import serialization

with open("private.pem","rb") as ficheiro:
        client_private_key = ficheiro.read()

client_private_key = load_pem_private_key(client_private_key,
                                          password=None)

server_private_key = ec.generate_private_key(ec.SECP521R1())

pem_server_private_key = server_private_key.private_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PrivateFormat.PKCS8,
    encryption_algorithm=serialization.NoEncryption()
)

with open("server_private.pem","wb") as file:
    file.write(pem_server_private_key)

shared_secret = client_private_key.exchange(ec.ECDH(), server_private_key.public_key())

derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,  
        salt=None,
        info=b"handshake data",
    ).derive(shared_secret)

with open(sys.argv[1],"rb") as f:
        plaintext = f.read()

padder = padding.PKCS7(128).padder()
padded_data = padder.update(plaintext)
padded_data += padder.finalize()

iv = b"1234567891011121"
cipher = Cipher(algorithms.AES(derived_key), modes.CBC(iv))
encryptor = cipher.encryptor()
encrypted_text = encryptor.update(padded_data) + encryptor.finalize()

with open("encrypted.txt","wb") as file:
        file.write(encrypted_text)


