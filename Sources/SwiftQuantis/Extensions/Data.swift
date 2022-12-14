import Foundation

extension Data {
    var hexadecimalString: String {
        // Convert the data to a hexadecimal string
        return map { String(format: "%02x", $0) }.joined()
    }
}
