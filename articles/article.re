=[nonum] SwiftLintのオレオレカスタムルール一覧

== はじめに

こんにちは、ウホーイ（@<href>{https://x.com/the_uhooi, @the_uhooi}）です。

SwiftLintで私が自作しているカスタムルールを紹介します。

== 環境

本稿の環境（2024/06/20現在）です。
多少環境が異なっても同様の動作になると思いますが、もし動作が異なっていたらX（旧Twitter）などでご連絡くださると嬉しいです。

 * OS: macOS Sonoma 14.5 (23F79)
 * Xcode: 15.4 (15F31d)
 * Swift: 5.10
 * SwiftLint: 0.55.1

== オレオレカスタムルール一覧

私が自作しているカスタムルールの一覧です。

=== enum_lower_case

enumのcase名の先頭が大文字より小文字を好むルールです。

//source[][]{
  enum_lower_case:
    name: 'Enum Lower Case'
    regex: '\bcase\s+([A-Z][a-zA-Z0-9]*)\b'
    capture_group: 1
    message: 'The enum case should be lower camel case'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
enum Foo {
  case bar
}

// Triggering Examples
enum Foo {
  case ↓Bar
}
//}

=== final_class

@<code>{class}に@<code>{final}を必ず付けるルールです。

//source[][]{
  final_class:
    name: 'Final Class'
    regex: '\b(?<!final)\s+(class)\b'
    capture_group: 1
    message: 'Always add `final` to classes that do not inherit'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
final class Foo {}

// Triggering Examples
↓class Foo {}
//}

=== date_now

@<code>{Date()}より@<code>{.now}を好むルールです。

@<code>{.now}は@<code>{Date()}と同等ですが、@<code>{.now}のほうがわかりやすいので好みです。

//source[][]{
  # iOS 15.0+
  date_now:
    name: 'Date Now'
    regex: '[=:(]\s*(Date\(\))'
    capture_group: 1
    message: 'Prefer using `.now` over `Date()`'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
let weekday = Calendar.current.component(.weekday, from: .now)

// Triggering Examples
let weekday = Calendar.current.component(.weekday, from: ↓Date())
//}

=== enumerated

@<code>{enumerated()}より@<href>{https://github.com/apple/swift-algorithms, swift-algorithms}の@<code>{indexed()}を好むルールです。

//source[][]{
  enumerated:
    name: 'Enumerated'
    regex: '.+\.(enumerated\([^)]*\))'
    capture_group: 1
    message: 'Prefer using `indexed()` over `enumerated()`'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
import Algorithms
ForEach(monsters.indexed(), id: \.element.id) { index, monster in
  // Do something
}

// Triggering Examples
ForEach(Array(monsters.↓enumerated()), id: \.element.id) { index, monster in
  // Do something
}
//}

=== aspect_ratio_fill

@<code>{.aspectRatio(contentMode: .fill)}より@<code>{.scaledToFill()}を好むルールです。

@<code>{.scaledToFill()}は@<code>{.aspectRatio(contentMode: .fill)}と同等ですが、短いほうが好みです。

//source[][]{
  # iOS 13.0+
  aspect_ratio_fill:
    name: 'Aspect Ratio Fill'
    regex: '.+\.(aspectRatio\(contentMode:\s*\.fill\s*\))'
    capture_group: 1
    message: 'Prefer using `scaledToFill()` over `aspectRatio(contentMode: .fill)`'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
Image(systemName: "swift")
  .resizable()
  .scaledToFill()

// Triggering Examples
Image(systemName: "swift")
  .resizable()
  .↓aspectRatio(contentMode: .fill)
//}

=== aspect_ratio_fit

@<code>{.aspectRatio(contentMode: .fit)}より@<code>{.scaledToFit()}を好むルールです。

@<code>{aspect_ratio_fill}と同じ理由でルール化しています。

//source[][]{
  # iOS 13.0+
  aspect_ratio_fit:
    name: 'Aspect Ratio Fit'
    regex: '.+\.(aspectRatio\(contentMode:\s*\.fit\s*\))'
    capture_group: 1
    message: 'Prefer using `scaledToFit()` over `aspectRatio(contentMode: .fit)`'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
Image(systemName: "swift")
  .resizable()
  .scaledToFit()

// Triggering Examples
Image(systemName: "swift")
  .resizable()
  .↓aspectRatio(contentMode: .fit)
//}

=== corner_radius

@<code>{cornerRadius()}は非推奨になったため、@<code>{clipShape()}または@<code>{fill()}を好むルールです。

@<code>{clipShape(RoundedRectangle(cornerRadius:))}に置き換えることが多いです。

//source[][]{
  # iOS 13.0+
  corner_radius:
    name: 'Corner Radius'
    regex: '.+\.(cornerRadius\([^)]*\))'
    capture_group: 1
    message: 'Prefer using `clipShape(RoundedRectangle(cornerRadius:))` or `fill()` over `cornerRadius()` because it was deprecated'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
Text("Foo")
  .clipShape(RoundedRectangle(cornerRadius: 8))

// Triggering Examples
Text("Foo")
  .↓cornerRadius(8)
//}

=== foreground_color

@<code>{foregroundColor(_:)}は非推奨になったため、@<code>{foregroundStyle(_:)}を好むルールです。

//source[][]{
  # iOS 15.0+
  foreground_color:
    name: 'Foreground Color'
    regex: '.+\.(foregroundColor\([^)]*\))'
    capture_group: 1
    message: 'Prefer using `foregroundStyle()` over `foregroundColor()` because it was deprecated'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
Text("Foo")
  .foregroundStyle(.blue)

// Triggering Examples
Text("Foo")
  .↓foregroundColor(.blue)
//}

=== navigation_bar_leading

@<code>{.navigationBarLeading}は非推奨になったため、@<code>{.topBarLeading}を好むルールです。

//source[][]{
  # iOS 14.0+
  navigation_bar_leading:
    name: 'Navigation Bar Leading'
    regex: '\bToolbarItem\(placement:\s*(.navigationBarLeading)\s*\)'
    capture_group: 1
    message: 'Prefer using `.topBarLeading` over `.navigationBarLeading` because it was deprecated'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
Text("Foo")
  .toolbar {
    ToolbarItem(placement: .topBarLeading) {
      // Do something
    }
  }

// Triggering Examples
Text("Foo")
  .toolbar {
    ToolbarItem(placement: ↓.navigationBarLeading) {
      // Do something
    }
  }
//}

=== navigation_bar_trailing

@<code>{.navigationBarTrailing}は非推奨になったため、@<code>{.topBarTrailing}を好むルールです。

//source[][]{
  # iOS 14.0+
  navigation_bar_trailing:
    name: 'Navigation Bar Trailing'
    regex: '\bToolbarItem\(placement:\s*(.navigationBarTrailing)\s*\)'
    capture_group: 1
    message: 'Prefer using `.topBarTrailing` over `.navigationBarTrailing` because it was deprecated'
    severity: warning
//}

//source[][swift]{
// Non Triggering Examples
Text("Foo")
  .toolbar {
    ToolbarItem(placement: .topBarTrailing) {
      // Do something
    }
  }

// Triggering Examples
Text("Foo")
  .toolbar {
    ToolbarItem(placement: ↓.navigationBarTrailing) {
      // Do something
    }
  }
//}

== おわりに

SwiftLintのカスタムルールは正規表現で書くので、慣れていないと難しいです。
私も試行錯誤しながら書いたので、誤りなどあればご連絡くださると嬉しいです。

== 参考資料

 * @<href>{https://github.com/uhooi/iOSDC-Japan-2024-Manuscript}
 * @<href>{https://qiita.com/uhooi/items/9deb56416aaa81709f69, SwiftLintのオレオレカスタムルール一覧 - Qiita}
