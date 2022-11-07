file(REMOVE_RECURSE
  "devel/lib/robotcorp/converter"
  "devel/lib/robotcorp/converter.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/converter.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
