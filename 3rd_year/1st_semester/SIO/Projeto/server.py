from flask import Flask,request,redirect, send_file
from cryptography.hazmat.primitives import hashes
import os
import json
import sys
import requests as rq
import base64
import datetime

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads/' # sets the default folder where the uploaded files are stored

organizations = {}

@app.route('/')
def home():
   return redirect("/organization/list")

@app.route("/organization/list")
def org_list():
    return json.dumps(organizations)

@app.route("/organization/create", methods = ["Post"])
def org_create():
    organizations[request.json["org_name"]] = {"files":list(), "metadata":list(),"subjects":list()}

@app.route("/organization/upload", methods=["Post"])
def upload_file():
    # unpack uploaded file and create correct path to store it
    file = base64.b64decode(request.json['file'])
    metadata = request.json['metadata']

    filename = file.split(".")[0] + ".txt"
    file_path = os.path.join(app.config['UPLOAD_FOLDER'],"files/")
    file_path = os.path.join(file_path,filename)

    metadata_filename = file.filename.split(".")[0] + "_metadata.json"
    metadata_filepath = os.path.join(app.config['UPLOAD_FOLDER'], "metadata/")
    metadata_filepath = os.path.join(metadata_filepath,metadata_filename)

    return "File upload sucessful"

@app.route("/organization/download", methods=['GET'])
def download_file():
    file = request.json["file_path"]
    return send_file(app.config['UPLOAD_FOLDER'] + file.split(".")[0] + ".json", as_attachment=True)
    

if __name__ == "__main__":
    app.run(debug=True)
