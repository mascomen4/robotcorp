file(REMOVE_RECURSE
  "devel/lib/libsender.pdb"
  "devel/lib/libsender.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sender.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
