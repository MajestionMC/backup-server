# Backup Your Server Files

This project is designed for Linux distributions.

## How to Install

1. Clone the project into the folder where you want to generate your backups, then navigate into the cloned directory.
   ```sh
   git clone git@github.com:MajestionMC/backup-server.git
   cd backup-server
   ```
1. Execute the Makefile.
    ```sh
    make install
    ```

## How to Remove
1. Execute the Makefile to clean up.
    ```sh
    make clean
    ```
2. Remove the project folder
    ```sh
    cd .. && rm -rf backup-server
    ```
