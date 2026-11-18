# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: Copyright (c) 2025, Lars Uffmann <coding23@uffmann.name>
# BSD-3-Clause License
#
#   Copyright (c) 2025, Lars Uffmann <coding23@uffmann.name>
#
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#   - Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   - Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#   - Neither the name of the author nor the
#     names of any contributors may be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
#   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

# #=======================================================================================================================
# # Transfer project variables to local constants needed for CPack
# #=======================================================================================================================
# set(GIT_COMMIT_ID "b5e903bb")
# set(GIT_COMMIT_ID_TIME "2026-11-18 13:40:10 +0300")

#=======================================================================================================================
# Set CPack options for debian package generation
#=======================================================================================================================
set(CPACK_PACKAGE_NAME "libopenxlsx")
set(CPACK_PACKAGE_CONTACT "coding23@uffmann.name")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lars Uffmann <coding23@uffmann.name>")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "") # TODO: set project dependencies here
set(CPACK_BINARY_DEB "ON") # TEST

set(CPACK_PACKAGE_VERSION_MAJOR ${OPENXLSX_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${OPENXLSX_MINOR_VERSION})
set(CPACK_VERSION_PATCH "${OPENXLSX_MICRO_VERSION}-${GIT_COMMIT_ID}")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_VERSION_PATCH}")
