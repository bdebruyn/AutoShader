set(sources
   MainArgs
   MockIPNFMessageAlt
   MyMessage
)
set(headersOnly
)
set(libraries
   CONAN_PKG::Framework
)
StaticLib_All("${sources}" "${headersOnly}" "${libraries}")
