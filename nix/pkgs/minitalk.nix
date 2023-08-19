{
  lib,
  stdenv,
  libft,
  libftprintf,
}:
stdenv.mkDerivation {
  pname = "minitalk";
  version = "0.1.0";
  src = ../../minitalk;
  buildInputs = [
    libft
  ];
  buildPhase = ''
    export LIBFTPRINTF_DIR="${libftprintf}"
    make
  '';
  installPhase = ''
    mkdir -p $out/bin
    cp client $out/bin
    cp server $out/bin
  '';
  meta = with lib; {
    license = licenses.agpl3Only;
  };
}
