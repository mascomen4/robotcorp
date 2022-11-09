file(REMOVE_RECURSE
  "devel/lib/libreceiver.pdb"
  "devel/lib/libreceiver.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/receiver.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
