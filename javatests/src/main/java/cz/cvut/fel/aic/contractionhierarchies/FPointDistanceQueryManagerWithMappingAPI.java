/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package cz.cvut.fel.aic.contractionhierarchies;

public class FPointDistanceQueryManagerWithMappingAPI {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected FPointDistanceQueryManagerWithMappingAPI(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(FPointDistanceQueryManagerWithMappingAPI obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        contractionHierarchiesJNI.delete_FPointDistanceQueryManagerWithMappingAPI(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void initializeCH(String chFile, String mappingFile) {
    contractionHierarchiesJNI.FPointDistanceQueryManagerWithMappingAPI_initializeCH(swigCPtr, this, chFile, mappingFile);
  }

  public double distanceQuery(java.math.BigInteger source, java.math.BigInteger target) {
    return contractionHierarchiesJNI.FPointDistanceQueryManagerWithMappingAPI_distanceQuery(swigCPtr, this, source, target);
  }

  public void clearStructures() {
    contractionHierarchiesJNI.FPointDistanceQueryManagerWithMappingAPI_clearStructures(swigCPtr, this);
  }

  public FPointDistanceQueryManagerWithMappingAPI() {
    this(contractionHierarchiesJNI.new_FPointDistanceQueryManagerWithMappingAPI(), true);
  }

}