## Server to Client

    [type:char][size:int32][message:buffer(size)]

- 'i': info
- 'e': error

## Client to Server

    [type:char][palettes:int32][boxes:int32][parts:int32][part_type:char]

- type: 'i' init
- part_type:

    [type:char][action:char]

- type: 'e': error handling
- action: 's': stop, 'c': continue
