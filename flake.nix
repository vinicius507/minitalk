{
  inputs = {
    nixpkgs.url = "nixpkgs";
    libft = {
      url = "github:vinicius507/libft";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = {
    self,
    nixpkgs,
    libft,
  }: let
    allSystems = [
      "x86_64-linux"
      "aarch64-linux"
    ];
    forEachSystem = f:
      nixpkgs.lib.genAttrs allSystems (system:
        f {
          pkgs = import nixpkgs {
            inherit system;
            overlays = [
              libft.overlays.libft
              libft.overlays.devshell
              self.overlays.minitalk
            ];
          };
        });
  in {
    checks = forEachSystem ({pkgs}: {
      norminette-check = pkgs.stdenvNoCC.mkDerivation {
        name = "norminette-check";
        src = ./minitalk;
        dontBuild = true;
        doCheck = true;
        checkPhase = with pkgs; ''
          ${norminette}/bin/norminette $src
        '';
        installPhase = "touch $out"; # Derivation must build an output.
      };
    });
    packages = forEachSystem ({pkgs}: {
      default = pkgs.minitalk;
      minitalk = import ./nix/pkgs/minitalk.nix {
        inherit (pkgs) lib libft;
        inherit (pkgs.llvmPackages_12) stdenv;
      };
    });
    overlays = {
      default = self.overlays.minitalk;
      minitalk = final: _: {
        minitalk = self.packages.${final.system}.minitalk;
      };
    };
    devShells = forEachSystem ({pkgs}: {
      default = pkgs.mkShell {
        packages = with pkgs; [
          bear
          clang-tools_12
          gnumake
          norminette
          valgrind
        ];
      };
    });
  };
}
