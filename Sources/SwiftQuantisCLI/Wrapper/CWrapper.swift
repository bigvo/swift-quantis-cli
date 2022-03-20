//
//  File.swift
//  
//
//  Created by Vladimir Young on 3/19/22.
//

import Foundation
import Quantis


var quantisError = QuantisError.self
//var quantisCount = QuantisCount(quantisDeviceType)
enum device: Int {
    case QUANTIS_DEVICE_PCI = 1
    case QUANTIS_DEVICE_USB = 2
}


public func quantisCount(device: UInt32) -> Int32 {
    let count = QuantisCount(QuantisDeviceType(device))
    return count
}

