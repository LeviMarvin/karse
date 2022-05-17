// Copyright (c) 2022 Levi Marvin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "key.h"

X509 *get_x509_cert_with_pem_file(const char *path)
{
    FILE *file_pem  = fopen(path, "r");
    X509 *x509_cert   = NULL;

    if (file_pem != NULL) {
        fputs("IO_FILE_OPEN_ERR", stderr);
        // Free all
        X509_free(x509_cert);
        fclose(file_pem);
    }
    if (!PEM_read_X509(file_pem, &x509_cert, NULL, NULL)) {
        fputs("IO_OSSL_X509_READ_FAILURE", stderr);
        // Free all
        X509_free(x509_cert);
        fclose(file_pem);
    } else if (x509_cert == NULL) {
        fputs("IO_OSSL_X509_READ_NULL", stderr);
        // Free all
        X509_free(x509_cert);
        fclose(file_pem);
    }

    return x509_cert;
}

X509_CRL *get_x509_crl_with_pem_file(const char *path)
{
    FILE *file_pem      = fopen(path, "r");
    X509_CRL *x509_cert = NULL;

    if (file_pem == NULL) {
        fputs("IO_FILE_OPEN_ERR", stderr);
        // Free all
        X509_CRL_free(x509_cert);
        fclose(file_pem);
    }
    if (!PEM_read_X509_CRL(file_pem, &x509_cert, NULL, NULL)) {
        fputs("IO_OSSL_X509CRL_READ_FAILURE", stderr);
        // Free all
        X509_CRL_free(x509_cert);
        fclose(file_pem);
    } else if (x509_cert == NULL) {
        fputs("IO_OSSL_X509CRL_READ_NULL", stderr);
        // Free all
        X509_CRL_free(x509_cert);
        fclose(file_pem);
    }

    return x509_cert;
}

EVP_PKEY *get_evp_pkey_prvkey_by_type_with_pem_file(const char *type, const char *path)
{
    FILE *file_prvkey      = fopen(path, "r");
    EVP_PKEY *pkey_prvkey  = NULL;
    RSA *rsa_prvkey        = NULL;
    DSA *dsa_prvkey        = NULL;
    EC_KEY *ec_prvkey      = NULL;
    pkey_prvkey            = EVP_PKEY_new();

    if (file_prvkey == NULL) {
        fputs("IO_FILE_OPEN_ERR", stderr);
        // Free all
        EVP_PKEY_free(pkey_prvkey);
        RSA_free(rsa_prvkey);
        DSA_free(dsa_prvkey);
        EC_KEY_free(ec_prvkey);
        fclose(file_prvkey);
    }
    if (!strcmp(type, "RSA")) {
        PEM_read_RSAPrivateKey(file_prvkey, &rsa_prvkey, NULL, NULL);
        if (rsa_prvkey == NULL) {
            fputs("IO_OSSL_RSA_READ_NULL", stderr);
            // Free all
            EVP_PKEY_free(pkey_prvkey);
            RSA_free(rsa_prvkey);
            DSA_free(dsa_prvkey);
            EC_KEY_free(ec_prvkey);
            fclose(file_prvkey);
        }
        EVP_PKEY_set1_RSA(pkey_prvkey, rsa_prvkey);
        // Free except RSA, EVP_PKEY and FILE
        DSA_free(dsa_prvkey);
        EC_KEY_free(ec_prvkey);
    } else if (!strcmp(type, "DSA")) {
        PEM_read_DSAPrivateKey(file_prvkey, &dsa_prvkey, NULL, NULL);
        if (dsa_prvkey == NULL) {
            fputs("IO_OSSL_DSA_READ_NULL", stderr);
            // Free all
            EVP_PKEY_free(pkey_prvkey);
            RSA_free(rsa_prvkey);
            DSA_free(dsa_prvkey);
            EC_KEY_free(ec_prvkey);
            fclose(file_prvkey);
        }
        EVP_PKEY_set1_DSA(pkey_prvkey, dsa_prvkey);
        // Free except DSA, EVP_PKEY and FILE
        RSA_free(rsa_prvkey);
        EC_KEY_free(ec_prvkey);
    } else if (!strcmp(type, "EC")) {
        pkey_prvkey = PEM_read_PrivateKey(file_prvkey, NULL, NULL, NULL);
        //ec_prvkey = EC_KEY_new();
        ec_prvkey = EVP_PKEY_get1_EC_KEY(pkey_prvkey);
        if (ec_prvkey == NULL) {
            fputs("IO_OSSL_EC_READ_NULL", stderr);
            // Free all
            EVP_PKEY_free(pkey_prvkey);
            RSA_free(rsa_prvkey);
            DSA_free(dsa_prvkey);
            EC_KEY_free(ec_prvkey);
            fclose(file_prvkey);
        }
        EVP_PKEY_set1_EC_KEY(pkey_prvkey, ec_prvkey);
        // Free except EC_KEY, EVP_PKEY and FILE
        RSA_free(rsa_prvkey);
        DSA_free(dsa_prvkey);
    } else {
        fputs("IO_OSSL_PRIKEY_LOAD_TYPE_UNKNOWN", stderr);
        // Free all
        EVP_PKEY_free(pkey_prvkey);
        RSA_free(rsa_prvkey);
        DSA_free(dsa_prvkey);
        EC_KEY_free(ec_prvkey);
        fclose(file_prvkey);
    }

    if (pkey_prvkey == NULL) {
        fputs("IO_OSSL_EVPPKEY_READ_NULL", stderr);
    }

    return pkey_prvkey;
}

RSA *get_rsa_prvkey_by_evp_pkey(EVP_PKEY *pkey)
{
    return EVP_PKEY_get1_RSA(pkey);
}

DSA *get_dsa_prvkey_by_evp_pkey(EVP_PKEY *pkey)
{
    return EVP_PKEY_get1_DSA(pkey);
}

EC_KEY *get_ec_key_prvkey_by_evp_pkey(EVP_PKEY *pkey)
{
    return EVP_PKEY_get1_EC_KEY(pkey);
}