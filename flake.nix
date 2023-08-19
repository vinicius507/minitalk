{
  inputs = {
    nixpkgs.url = "nixpkgs";
    ft-nix = {
      url = "github:vinicius507/42-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    libft = {
      url = "github:vinicius507/libft";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    ft_printf = {
      url = "github:vinicius507/ft_printf";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = {
    self,
    nixpkgs,
    ft-nix,
    libft,
    ft_printf,
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
              ft-nix.overlays.norminette
              ft_printf.overlays.libftprintf
              libft.overlays.libft
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
        inherit (pkgs) lib libft libftprintf;
        inherit (pkgs.llvmPackages_12) stdenv;
      };
    });
    overlays = {
      default = self.overlays.minitalk;
      minitalk = final: _: {
        minitalk = self.packages.${final.system}.minitalk;
      };
    };
    devShells = forEachSystem ({pkgs}: let
      mkShell = pkgs.mkShell.override {inherit (pkgs.llvmPackages_12) stdenv;};
    in {
      default = mkShell {
        packages = with pkgs;
          [
            bear
            clang-tools_12
            gnumake
            norminette
            valgrind
          ]
          ++ [pkgs.libft pkgs.libftprintf];
      };
    });
  };
}
