using System.Windows.Media.Imaging;
using WpfMath.Parsers;
using WpfMath.Rendering;
using XamlMath;
using XamlMath.Exceptions;

namespace LaTex {
    class Program
    {
        [STAThread]
        static int Main(string[] args)
        {
            string command = "test";
            string latex = "Test";
            string fileName = "test.png";
            int textStyle = 0;
            string font = "Arial";

            if (args.Length >= 1) latex = args[0];
            if (args.Length >= 2) latex = args[1];
            if (args.Length >= 3) fileName = args[2];

            try
            {
                var parser = WpfTeXFormulaParser.Instance;
                var formula = parser.Parse(latex);


                if (command == "gen") try
                {
                    var environment = WpfTeXEnvironment.Create((TexStyle)textStyle, 100, font);
                    var bitmapSource = formula.RenderToBitmap(environment, 100);
                    var encoder = new PngBitmapEncoder();
                    encoder.Frames.Add(BitmapFrame.Create(bitmapSource));
                    using (var target = new FileStream(fileName, FileMode.Create))
                    {
                        encoder.Save(target);
                    }
                }
                catch
                {
                    return 2;
                }

            }
            catch
            {
                return 1;
            }

            return 0;
        }
    
    }
}