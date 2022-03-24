# Swift-Quantis-CLI

A simple Swift C wrapper for id Quantique Quantis: Quantum Random Number Generator.

## Requirements:
System: Unix, Library: libusb-1.0

Compile providing required flag to Swift Linker: swift build -Xlinker -lusb-1.0

## CLI Commands
```
  -i, --info              Print all cards info
  --roll                  Roll from 1 to 100, like in WoW.
                          Optionally Device Number and Device Type can be passed.
                          Example: roll -t 2 -n 0
  --jackpot               Roll a jackpot, receive result from 0.00 to 100.00.
  --coinflip              Flip a coin, result: 1 or 2.
  --wheel                 Roll a wheel, result from 1.00 to 25.99
  --randomint             Random number, from -min to -max, if no value provided, default: 1 to 10 will be used
  --randomdouble          Random double, from -min to -max, if no value provided, default: 1.00 to 10.00 will be used
  --min <min>             From minimal number
  --max <max>             To maximum number
  -t <t>                  Device Type: 1 - PCI-E, 2  - USB
  -n <n>                  Device Number
  -h, --help              Show help information.
```

## Example
```
--roll -t 2 -n 0
--jackpot
--coinflip -t 1 -n 1
--randomint --min 1 --max 100
```
