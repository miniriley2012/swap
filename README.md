# Swap

A small utility to swap the names of two files.

## Usage

```shell
swap [-v] file1 file2
```

## Known Issues

On systems that support `RENAME_EXCHANGE` (or `RENAME_SWAP` on macOS) swap will issue a system call that
should make the operation atomic. If this is not the case, swap will rename the first file to a temporary name
while swapping. If there is a failure for some reason while the first file still has the temporary name, swap will not
attempt to undo the operation. I intend for the slow method of swapping to be an atomic operation in the future. 
