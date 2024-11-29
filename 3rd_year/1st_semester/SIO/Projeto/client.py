import requests as rq
import sys
import os
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.serialization import load_pem_public_key,load_pem_private_key
import base64
import datetime

if sys.argv[1] == "-u":
    url = 'http://127.0.0.1:5000/organization/upload'

    with open("/home/giboia/Desktop/SO/Aula1/lesson-1/as-library/linked-list.cpp","rb") as f:
        file = f.read()

    with open("public.pem","rb") as ficheiro:
        client_public_key = ficheiro.read()

    client_public_key = load_pem_public_key(client_public_key,password=None)

    file_copy = file[:]
    digest = hashes.Hash(algorithm=hashes.SHA256())
    digest.update(file_copy.encode())

    file = base64.b64encode(file).decode("ascii")
    file_copy = base64.b64encode(file_copy).decode("ascii")
    
    request = rq.post(url,json={
        "file":file,
        "metadata" :{"document_handle":"a", 
                    "name":sys.argv[2], 
                    "create_date":datetime.datetime.now().strftime('%d/%m/%Y'), 
                    "creator":"a", 
                    "file_handle": file_copy, 
                    "acl":"a", 
                    "deleter":"a", 
                    "alg":"?", 
                    "key":""},
     })

if sys.argv[1] == "-d":
    url = 'http://127.0.0.1:5000/organization/download'

    request = rq.get(url,json={"file_path":"linked-list.cpp"})

#url = 'http://127.0.0.1:5000/organization/create'
#request = rq.get(url,json={"org_name":"nome"})
