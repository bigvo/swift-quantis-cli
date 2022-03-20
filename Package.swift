// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "SwiftQuantisCLI",
    platforms: [
        .macOS(.v12)
    ],
//    products: [
//        // Products define the executables and libraries a package produces, and make them visible to other packages.
//        .library(name: "SwiftQuantisCLI", targets: ["SwiftQuantisCLI", "Quantis"]),
//    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-argument-parser", from: "1.1.0"),
        .package(url: "https://github.com/libusb/libusb", from: "1.0.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(name: "Quantis", path: "./Sources/Quantis"),
        .executableTarget(name: "SwiftQuantisCLI", dependencies: [
            "Quantis",
            .product(name: "ArgumentParser", package: "swift-argument-parser"),
            .product(name: "libusb", package: "libusb")
        ]),
//        .executableTarget(name: "SwiftQuantisCLI", dependencies: [.target(name: "ArgumentParser")]),
//        .testTarget(name: "Test1Tests", dependencies: ["Test1"]),
    ]
)
