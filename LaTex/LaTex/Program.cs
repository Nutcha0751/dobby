using System.Windows.Media.Imaging;
using WpfMath.Parsers;
using WpfMath.Rendering;
using XamlMath;

namespace LaTex {
    class Program
    {
        static void Main(string[] args)
        {
            if(args.Length == 0)
            {
                return;
            }

            string latex = args[0];
            string fileName = args[1];

            var parser = WpfTeXFormulaParser.Instance;
            var formula = parser.Parse(latex);
            var environment = WpfTeXEnvironment.Create(TexStyle.Display, 100.0, "Arial");
            var bitmapSource = formula.RenderToBitmap(environment,100);

            var encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bitmapSource));
            using (var target = new FileStream(fileName, FileMode.Create))
            {
                encoder.Save(target);

            }

            return;
        }
    }
}