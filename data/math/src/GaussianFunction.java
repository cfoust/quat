/**
 * Created by caleb on 3/2/16.
 */
public class GaussianFunction {
    double mean, stdDev;

    public GaussianFunction(double mean, double stdDev) {
        this.mean = mean;
        this.stdDev = stdDev;
    }

    public double eval(double x) {
        return Math.exp(-1*Math.pow(x - mean, 2.0f) / (2 * Math.pow(stdDev, 2))) / (Math.sqrt(Math.PI * 2) * stdDev);
    }
}
