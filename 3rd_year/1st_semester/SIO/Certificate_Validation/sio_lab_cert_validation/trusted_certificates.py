import os
from validity_check import valid
from cryptography import x509

def trusted(dir_name: str) -> dict:
    """This function reads all the certificates saved in the given directory, returning them in a dictionary
    
    Args:
        dir_name (str): directory name where the certificates are saved

    Returns:
        dict: dictionary with keys as the certificates subjects and as values the corresponding certificates
    """
    result = {}
    certificates = [i.name for i in os.scandir(dir_name) if i.name.split('.')[::-1][0] == 'pem']

    for i in certificates:
        with open(dir_name+'/'+i,'rb') as file:
            cert = file.read()
        cert = x509.load_pem_x509_certificate(cert)
        if valid(cert):
            if cert.subject in result.keys():
                result[cert.subject].append(cert)
            else:
                result[cert.subject] = [cert]
    return result

def main():
    trust_certs = trusted("/etc/ssl/certs")
    print(f"{len(trust_certs)} valid trusted certificates found")
            

if __name__ == "__main__":
    main()
