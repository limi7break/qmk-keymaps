# qmk-keymaps

A repository containing my keymaps for QMK keyboards.

It contains [QMK Firmware](https://github.com/qmk/qmk_firmware) as a submodule.  
The compilation script works by symlinking a keymap into the submodule.

## Folder structure

The folder structure is `<keyboard>/<keymap>`:

```
crkbd
└── limi7break
    ├── config.h
    ├── keymap.c
    ├── rgb_matrix_user.inc
    └── rules.mk
```

## Usage

-   Clone the repository:

    ```bash
    git clone https://github.com/limi7break/qmk-keymaps.git
    cd qmk-keymaps
    ```

-   Compile a keymap:

    ```bash
    # ./compile <keyboard>/<keymap>
    ./compile crkbd/limi7break
    ```
