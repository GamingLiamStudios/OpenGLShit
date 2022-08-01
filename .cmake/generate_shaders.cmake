# Generates a source file to be included in the exectuable
# that contains exports of strings for the shader files.
# This is then externally included in 'shaders.h'

# Strip illegal characters
file(READ ${SHADER_FILE} SHADER_SOURCE)
string(REPLACE "\n" "\\n" SHADER_SOURCE ${SHADER_SOURCE})
string(REPLACE "\"" "\\\"" SHADER_SOURCE ${SHADER_SOURCE})

# Write SHADER_SOURCE to a file to be included in the executable
file(WRITE ${CSHADER_NAME} "const char *${SHADER_NAME} = \"${SHADER_SOURCE}\";")