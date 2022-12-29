"""
Copyright (C) 2022 QUSIDE TECHNOLOGIES - All Rights Reserved.

Unauthorized copying of this file, via any medium is strictly prohibited.
"""
# import the module
from QusideQRNGLALUser.quside_QRNG_LAL_User import QusideQRNGLALUser


if __name__ == '__main__':
    """ To initialize the class is need the QRNG IP address. """
    lib = QusideQRNGLALUser(ip='xxx.xxx.xxx.xxx')

    """ This variable has to be set to 0. """
    devIndex = 0

    # Get extracted random numbers in bytes
    captured_bytes = lib.get_random(1024, devIndex)

    print(captured_bytes)

    """
    This function disconnect the QRNG.
    NOTE:
        IT IS MANDATORY TO EXECUTE THIS FUNCTION BEFORE PROCESSING THE DATA OR PERFORMING ANY TASK THAT DOES NOT
        REQUIRE THE QRNG TO FREE THE CONNECTION WITH IT.
    """
    lib.disconnect()
