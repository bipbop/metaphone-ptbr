{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "./lib/"
      ],
      "cflags": ["-Wstack-protector"],
      "target_name": "addon",
      "sources": [ './lib/metaphone_ptbr.c', 'main.cpp' ]
    }
  ]
}