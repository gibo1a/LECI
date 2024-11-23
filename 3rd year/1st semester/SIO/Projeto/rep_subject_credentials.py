from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
import sys
import os

kdf = PBKDF2HMAC(
    algorithm=hashes.SHA256(),
    length=32,
    salt=os.urandom(8),
    iterations=480000,
)
derived_password = kdf.derive(sys.argv[1].encode())

private_key = ec.derive_private_key(derived_password,ec.SECP521R1())   #criar chave privada através de uma password
public_key = private_key.public_key()

pem_private_key = private_key.private_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PrivateFormat.PKCS8,
    encryption_algorithm=serialization.NoEncryption()
)


pem_public_key = public_key.public_bytes(
  encoding=serialization.Encoding.PEM,
  format=serialization.PublicFormat.SubjectPublicKeyInfo
)

with open("private.pem","wb") as file:
    file.write(pem_private_key)

with open("public.pem","wb") as file:
    file.write(pem_public_key)