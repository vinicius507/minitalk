<p align="center">
    <img src="https://game.42sp.org.br/static/assets/achievements/minitalkm.png">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/OS-Linux-blue" alt="OS">
    <img src="https://img.shields.io/badge/Language-C-orange.svg" alt="Language">
    <img src="https://img.shields.io/badge/Grade-125%2F100-brightgreen.svg" alt="Grade">
    <img src="https://img.shields.io/badge/Status-Completed-brightgreen.svg" alt="Status">
</p>

# Minitalk
[![build](https://github.com/vinicius507/minitalk/actions/workflows/build.yml/badge.svg)](https://github.com/vinicius507/minitalk/actions/workflows/build.yml)
[![norminette](https://github.com/vinicius507/minitalk/actions/workflows/norminette.yml/badge.svg)](https://github.com/vinicius507/minitalk/actions/workflows/norminette.yml)

This repository contains my submission of the Minitalk project for 42 School.
It provides a client and a server application which communicates with each other using signals.

## Introduction
The **minitalk** project provides two programs, a `server` and a `client`, which communicate with one another using Linux signals.

It works by interpreting the bits that compose the message as Linux signals, using `SIGUSR1`and `SIGUSR2` as `0` and `1`, respectively.

## Usage
To use the **minitalk** programs, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the repository's root directory.
3. Run `make` to compile the library.

Two compiled binaries, `client` and `server` will be available at the project repository.

Starting the server:

```sh
$ ./server
[SERVER] running on PID: 13290
```

Sending messages using the client:

```sh
$ ./client --help
Usage: ./client SERVER_PID MESSAGE
$ ./client 13290 "Hello, world!"
```
