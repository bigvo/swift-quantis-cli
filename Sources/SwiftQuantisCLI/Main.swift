//
//  Main.swift
//  
//
//  Created by Vladimir Young on 3/19/22.
//

import Foundation
import ArgumentParser
import SwiftQuantis

@main
struct QuantisCLI: ParsableCommand {
    @Flag(name: [.short, .long], help: "Print all cards info")
    var info: Bool = false
    
    @Flag(name: [.customLong("roll")], help:
            """
            Roll from 1 to 100, like in WoW.
            Optionally Device Number and Device Type can be passed.
            Example: roll -t 2 -n 0
            """)
    var makeRoll: Bool = false
    
    @Flag(name: [.customLong("jackpot")], help:
            """
            Roll a jackpot, receive result from 0.00 to 100.00.
            """)
    var rollJackpot: Bool = false
    
    @Flag(name: [.customLong("coinflip")], help:
            """
            Flip a coin, result: 1 or 2.
            """)
    var makeFlip: Bool = false
    
    @Flag(name: [.customLong("wheel")], help:
            """
            Roll a wheel, result from 1.00 to 25.99
            """)
    var rollWheel: Bool = false
    
    @Flag(name: [.customLong("randomint")], help:
            """
            Random number, from -min to -max, if no value provided, default: 1 to 10 will be used
            """)
    var randomInt: Bool = false
    
    @Flag(name: [.customLong("randomdouble")], help:
            """
            Random double, from -min to -max, if no value provided, default: 1.00 to 10.00 will be used
            """)
    var randomDouble: Bool = false
    
    @Option(name: .long, help: "From minimal number")
    var min: Double?
    
    @Option(name: .long, help: "To maximum number")
    var max: Double?
    
    @Option(name: .short, help: "How many numbers generate")
    var count: Int?
    
    @Option(name: .short, help: "Device Type: 1 - PCI-E, 2  - USB")
    var type: UInt32?
    
    @Option(name: .short, help: "Device Number")
    var number: UInt32?
    
    mutating func run() throws {
        let quantis = Quantis(device: QuantisDevice(type ?? 2), deviceNumber: number ?? 0)
        
        if info {
            quantis.printAllCards()
            return
        }
        
        if makeRoll {
            do {
                try print(quantis.roll())
                return
            } catch {
                print(error)
                fatalError()
            }
        }
        
        if rollJackpot {
            do {
                try print(quantis.jackpot())
                return
            } catch {
                print(error)
                fatalError()
            }
        }
        
        if makeFlip {
            do {
                try print(quantis.coinflip())
                return
            } catch {
                print(error)
                fatalError()
            }
        }
        
        if rollWheel {
            do {
                try print(quantis.wheel())
                return
            } catch {
                print(error)
                fatalError()
            }
        }
        
        if randomInt {
            do {
                if count != nil {
                    try print(quantis.quantisReadScaledIntArray(count: count!,
                        min: Int32(min ?? 1.00),
                        max: Int32(max ?? 100.00)
                    ))
                    return
                }
                try print(quantis.quantisReadScaledInt(
                        min: Int32(min ?? 1),
                        max: Int32(max ?? 10)))
                return
            } catch {
                print(error)
                fatalError()
            }
        }
        
        if randomDouble {
            do {
                try print(quantis.quantisReadScaledDouble(
                    min: min ?? 1.00,
                    max: max ?? 10.00
                ))
                return
            } catch {
                print(error)
                fatalError()
            }
        }
        return quantis.printAllCards()
    }
}
