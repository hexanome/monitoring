# Server to Client

## Message

    [type:char][size:int32][message:buffer(size)]

type:
- 'i': info
- 'e': error

# Client to Server

## Init

    [type:char][

type:
- 'i': init

## Handle errors

    [type:char][action:char]

type:
- 'e': error handling

action:
- 's': stop
- 'c': continue
