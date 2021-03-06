// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-quantis-cli",
    products: [
        .library(name: "SwiftQuantis", targets: ["SwiftQuantis"]),
        .executable(name:"SwiftQuantisCLI", targets: ["SwiftQuantisCLI"]),
    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-argument-parser", from: "1.1.0"),
    ],
    targets: [
        .target(name: "СQuantis", path: "./Sources/СQuantis"),
        .target(name: "SwiftQuantis", dependencies: [
            "СQuantis",
            "CLibUSB",
        ]),
        .executableTarget(name: "SwiftQuantisCLI", dependencies: [
            "СQuantis",
            "SwiftQuantis",
            "CLibUSB",
            .product(name: "ArgumentParser", package: "swift-argument-parser"),
        ]),
        .systemLibrary(
            name: "CLibUSB",
            pkgConfig: "libusb-1.0",
            providers: [
                .brew(["libusb"]),
                .apt(["libusb-1.0-0-dev"]),
            ]),
    ]
)
