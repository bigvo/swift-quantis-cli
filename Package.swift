// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-quantis-cli",
    products: [
        .library(name: "SwiftQuantis", targets: ["SwiftQuantisCLI"]),
        .executable(name:"SwiftQuantisCLI", targets: ["SwiftQuantisCLI"]),
    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-argument-parser", from: "1.1.0"),
    ],
    targets: [
        .target(name: "Quantis", path: "./Sources/Quantis"),
        .target(name: "SwiftQuantisCLI", dependencies: [
            "Quantis",
            .product(name: "ArgumentParser", package: "swift-argument-parser"),
        ]),
    ]
)
