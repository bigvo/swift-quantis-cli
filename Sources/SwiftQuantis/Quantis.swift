//
//  Quantis.swift
//  
//
//  Created by Vladimir Young on 3/19/22.
//
// QuantisDevice:
// 1 = QUANTIS_PCI_DEVICE
// 2 = QUANTIS_USB_DEVICE

import Foundation
import СQuantis

public typealias Quantis = QuantisFunctions

public typealias QuantisDevice = QuantisDeviceType

public final class QuantisFunctions {
    private var device: QuantisDevice
    private var deviceNumber: UInt32

    public init(device: QuantisDevice, deviceNumber: UInt32) {
        self.device = device
        self.deviceNumber = deviceNumber
    }
    
    public func quantisCount() -> Int32 {
        let count = QuantisCount(device)
        return count
    }
    
    public func printAllCards() {
        
        func printInfo(device: UInt32) {
            let driverVersion = QuantisGetDriverVersion(QuantisDevice(device))
            let deviceCount = QuantisCount(QuantisDevice(device))
            
            if driverVersion < 0.0 {
                print("Error while getting driver version.\n")
            }
            print(" Using driver version: \(driverVersion)\n")
            
            print(" Found card(s): \(deviceCount)\n")
            
            if deviceCount > 0 {
                for i in 1 ... deviceCount {
                    let deviceNumber = UInt32(i-1)
                    let boardVersion = QuantisGetBoardVersion(QuantisDevice(device), UInt32(deviceNumber))
                    let serialNumber = String(cString: (QuantisGetSerialNumber(QuantisDevice(device), UInt32(deviceNumber))))
                    let manufacturer = String(cString: (QuantisGetManufacturer(QuantisDevice(device), UInt32(deviceNumber))))
                    
                    print("     - Details for device #\(deviceNumber)")
                    print("      core version: \(boardVersion)")
                    print("      serial number: \(serialNumber)")
                    print("      manufacturer: \(manufacturer)")
                }
            }
        }
        
        print("""
                                                     '`.
                          .l<>>!:'               .;>~<>+<'
                         .__^`^;>+<:           ^>_>,'  .-_
                         '[:      :<_!'      ^<_l.      ![.
                        `i]-~I      `i-i'  '<-I         ~-
                       ']]]]]]<       '>-;;-i.         .]!
                       .+]]]]]l         ;[[i           i].
                         ,l>[;         ;_;^+>.        `[I
                            ~?^^,,:;;;<[+Il![]l:;;:,"`-_
                     `,I!><<<-]>!!lI![+,,:::";][lI!!!]]<<<>i;I><i,
                 ^l<~<iI,^'. .++   `-i        .~+.  I]^ .'`I[]]]]]>
               `<_l".         ._-.,[!           i[,I[,     .-]]]]]__:
               +]               >-];             :[],       .I>>l^ i['
               `~+l^            ,][,             l]]!           .,<_;
                 "!<~>!;,`.    "]:^-!           i-''?i   .`^:l>~~>;.
                    .^:li><<<>i]]I;i]_,",,,,,,,+[iIl~]~><<<>!;"'
                           .'`]_":;;;i]?ll!!I+]<;;;:":[!
                             l]'      ^~<'  l-;       I[^
                            '[l         l-i~+`         +-
                            i]           <]]I          `[I
                            ?>    `i+_~!_<.`~_I.        +_
                           .[I   .?]]]]]_    ^<_i^      i[
                            -+   '-]]]]]l      'l~~!,`'"]<
                            `+~i<~>;Il;`          ^Ii<<<I
                              '^` \n
            Swift Quantis CLI - Displaying devices info:\n
            """)
        
        print(" Searching for PCI-E devices...")
        printInfo(device: 1)
        
        print("-----------------")
        print(" Searching for USB devices...")
        printInfo(device: 2)
    }
    
    public func roll() throws -> Int32 {
        let min: Int32 = 1
        let max: Int32 = 100
        let pointer = UnsafeMutablePointer<Int32>.allocate(capacity: 1)
        let deviceHandle = QuantisReadScaledInt(device, deviceNumber, pointer, min, max)
        
        defer {
            pointer.deinitialize(count: 1)
            pointer.deallocate()
        }
        
        let result = pointer.pointee
        
        // Check if device is in working state.
        if deviceHandle != 0 {
            throw QuantisError.deviceError
        }
        
        // Check if result is correct.
        if result < min || result > max {
            throw QuantisError.noResult
        }
        return result
    }
    
    public func jackpot() throws -> Double {
        let min: Double = 0.01
        let max: Double = 100.00
        let pointer = UnsafeMutablePointer<Double>.allocate(capacity: 1)
        let deviceHandle = QuantisReadScaledDouble(device, deviceNumber, pointer, min, max)
        
        defer {
            pointer.deinitialize(count: 1)
            pointer.deallocate()
        }
        
        let result = pointer.pointee
        
        if deviceHandle != 0 {
            throw QuantisError.deviceError
        }
        
        if result < min || result > max {
            throw QuantisError.noResult
        }
        return Double(result).round(to: 2)
    }
    
    public func coinflip() throws -> Int32 {
        let min: Int32 = 1
        let max: Int32 = 2
        let pointer = UnsafeMutablePointer<Int32>.allocate(capacity: 1)
        let deviceHandle = QuantisReadScaledInt(device, deviceNumber, pointer, min, max)
        
        defer {
            pointer.deinitialize(count: 1)
            pointer.deallocate()
        }
        
        let result = pointer.pointee
        
        if deviceHandle != 0 {
            throw QuantisError.deviceError
        }
        
        if result < min || result > max {
            throw QuantisError.noResult
        }
        return result
    }
    
    public func wheel() throws -> Double {
        let min: Double = 1.00
        let max: Double = 25.99
        let pointer = UnsafeMutablePointer<Double>.allocate(capacity: 1)
        
        let deviceHandle = QuantisReadScaledDouble(device, deviceNumber, pointer, min, max)
        
        defer {
            pointer.deinitialize(count: 1)
            pointer.deallocate()
        }
        
        let result = pointer.pointee
        
        if deviceHandle != 0 {
            throw QuantisError.deviceError
        }
        
        if result < min || result > max {
            throw QuantisError.noResult
        }
        return Double(result).round(to: 2)
    }
    
    public func quantisReadScaledInt(min: Int32, max: Int32) throws -> Int32 {
        let pointer = UnsafeMutablePointer<Int32>.allocate(capacity: 1)
        
        let deviceHandle = QuantisReadScaledInt(device, deviceNumber, pointer, min, max)
        defer {
            pointer.deinitialize(count: 1)
            pointer.deallocate()
        }
        
        // If not check for min > max device gets in error state and stop working.
        if min > max {
            throw QuantisError.invalidParameters
        }
        
        let result = pointer.pointee
        
        if deviceHandle != 0 {
            throw QuantisError.deviceError
        }
        
        if result < min || result > max {
            throw QuantisError.noResult
        }
        return result
    }
    
    public func quantisReadScaledDouble(min: Double, max: Double) throws -> Double {
        let pointer = UnsafeMutablePointer<Double>.allocate(capacity: 1)
        
        let deviceHandle = QuantisReadScaledDouble(device, deviceNumber, pointer, min, max)
        defer {
            pointer.deinitialize(count: 1)
            pointer.deallocate()
        }
        
        if min > max {
            throw QuantisError.invalidParameters
        }
        
        let result = pointer.pointee
        
        if deviceHandle != 0 {
            throw QuantisError.deviceError
        }
        
        if result < min || result > max {
            throw QuantisError.noResult
        }
        return Double(result).round(to: 2)
    }
    
    public func quantisReadScaledIntArray(count: Int, min: Int32, max: Int32) throws -> [Int32] {
        if min > max {
            throw QuantisError.invalidParameters
        }
        
        // Calculate size of the data to be generated
        let size = MemoryLayout<Int32>.size * count
        
        if size > 16 * 1024 * 1024 {
            throw QuantisError.tooLargeRequest
        }
        
        // Allocate memory for the requested amount of Int32
        let pointer = UnsafeMutableRawPointer.allocate(byteCount: size, alignment: MemoryLayout<Int32>.alignment)
        
        let deviceHandle = QuantisRead(device, deviceNumber, pointer, size)
        
        defer {
            pointer.deallocate()
        }
        
        if deviceHandle < 0 {
            throw QuantisError.deviceError
        }
        
        let range: Int32 = (max - min) + 1
        var result: [Int32] = []
        
        for i in 0..<count {
            // Convert value to Int32
            let value = pointer.load(fromByteOffset: MemoryLayout<Int32>.size * i, as: Int32.self)
            // Scale in the required range
            let scaledValue = (value % range + range) % range + min
            result.append(scaledValue)
        }
        
        guard !result.isEmpty else {
            throw QuantisError.noResult
        }
        
        return result
    }
    
    public func quantisStringArray(count: Int, length: Int) throws -> [String] {
        // Calculate size of the data to be generated
        let size = count * length
        // Allocate and initialize data with zero
        var buffer = Data(count: size)
        
        if buffer.count > 16 * 1024 * 1024 {
            throw QuantisError.tooLargeRequest
        }
        
        let _ = buffer.withUnsafeMutableBytes {
            QuantisRead(device, deviceNumber, $0.baseAddress!, size)
        }
        
        let hexadecimalStrings = (0..<count).map { i in
            let subdata = buffer.subdata(in: i * length..<(i + 1) * length)
            return subdata.map { String(format: "%02x", $0) }.joined()
        }
        return hexadecimalStrings
    }
}
