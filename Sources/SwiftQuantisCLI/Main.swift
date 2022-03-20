//
//  Main.swift
//  
//
//  Created by Vladimir Young on 3/19/22.
//

import Foundation
import ArgumentParser

@main
struct QuantisCLI: ParsableCommand {
    @Option(name: [.short, .customLong("test")], help: "Test function")
    var test: Int
    
    mutating func run() throws {
        //        var test32: UInt32 = test
        print(quantisCount(device: UInt32(test)))
    }
}
