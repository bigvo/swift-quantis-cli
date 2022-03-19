//
//  File.swift
//  
//
//  Created by Vladimir Young on 3/19/22.
//

import Foundation
import Quantis

var quantisDeviceType = QuantisDeviceType(0)
var quantisError = QuantisError(0)
var quantisCount = QuantisCount(quantisDeviceType)

public func quantisCount(quantisDeviceType: Int) -> Int {
    return quantisCount(quantisDeviceType: quantisDeviceType)
}

