/**
 * SMTP email client
 *
 * Adapted from the `ssl_mail_client` example in mbedtls.
 *
 * Original Copyright (C) 2006-2016, ARM Limited, All Rights Reserved, Apache 2.0 License.
 * Additions Copyright (C) Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD, Apache 2.0 License.
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SMTP_CLIENT_H
#define __SMPT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
/**
 * @brief      Performs email send operation.The parameters used in the process must have been already set with menuconfig (for e.g. sender, reciever etc.)
 *
 *
 * @param[in]  email_data       pointer to the data that is to be sent as attachment
 *
 * @param[in]  email_data_size  size of the data
 *
 * @return
 *            - ESP_OK          if mail send operation is successfull
 *            - ESP_FAIL        if mail send operaion is failed
 */
esp_err_t smtp_client_send_email(uint8_t *email_data, int email_data_size);
#ifdef __cplusplus
}
#endif
#endif
