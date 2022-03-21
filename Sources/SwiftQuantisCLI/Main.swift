//
//  Main.swift
//  
//
//  Created by Vladimir Young on 3/19/22.
//

import Foundation
import ArgumentParser
import Quantis

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
    
    @Option(name: .short, help: "Device Type: 1 - PCI-E, 2  - USB")
    var type: UInt32?
    
    @Option(name: .short, help: "Device Number")
    var number: UInt32?
    
    mutating func run() throws {
        if info {
            printAllCards()
        }
        
        if makeRoll {
            print(roll(deviceType: QuantisDeviceType(type ?? 2), deviceNumber: number ?? 0))
        }
        
        if rollJackpot {
            print(jackpot(deviceType: QuantisDeviceType(type ?? 2), deviceNumber: number ?? 0))
        }
        
        if makeFlip {
            print(coinflip(deviceType: QuantisDeviceType(type ?? 2), deviceNumber: number ?? 0))
        }
    }
}
