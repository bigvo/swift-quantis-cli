//
//  Models.swift
//  
//
//  Created by Vladimir Young on 3/21/22.
//

import Foundation

extension Double {
    func round(to places: Int) -> Double {
        let divisor = pow(10.0, Double(places))
        return (self * divisor).rounded() / divisor
    }
}
