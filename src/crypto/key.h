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

#ifndef KARSE_KEY_H
#define KARSE_KEY_H

#include "crypto.h"

#include "../io/file/file.h"

X509 *get_x509_cert_with_pem_file(const char *path);
X509_CRL *get_x509_crl_with_pem_file(const char *path);
EVP_PKEY *get_evp_pkey_privkey_by_type_with_pem_file(const char *type, const char *path);
RSA *get_rsa_privkey_by_evp_pkey(EVP_PKEY *pkey);
DSA *get_dsa_privkey_by_evp_pkey(EVP_PKEY *pkey);
EC_KEY *get_ec_key_privkey_by_evp_pkey(EVP_PKEY *pkey);

#endif //KARSE_KEY_H
